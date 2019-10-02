import numpy as np
import math

class KFSim(object):

    def __init__(self, resultsFileName, maxSteps, seed, numStateFrames):
        self.rng1 = np.random.RandomState(seed)
        #self.maxHeadingIncrement = 0.2
        self.resultsFileName = resultsFileName
        self.gtLocation = (0.0, 0.0)
        self.estLocation = (0.0, 0.0)
        self.gtVelocity = (0.0, 0.0)
        self.estVelocity = (0.0, 0.0)
        self.destination = (0.0, 0.0)
        self.cumulativeReward = 0.0
        self.currentHeading = math.pi / 2.0

        self.uuvSpeed = 3.2
        #self.sensorNoiseStdev = 8.0
        self.wcRegionY1 = 0.0
        self.wcRegionY2 = 0.0
        self.defaultControls = [1.0, 0.0, 0.0, 1.0,
                                0.3, 0.0, 0.0, 0.3,
                                0.1, 0.0, 0.0, 0.2,
                                0.0, 0.0, 0.0, 0.0]
        self.waterCurrentVector = (0.0, 0.0)
        self.threshold = 10.0
        self.initialDist = 0.0

        self.numStateFrames = numStateFrames
        self.state = []
        self.stateWindow = []
        self.numSteps = 0
        self.steps = 0
        self.maxSteps = maxSteps
        self.P = np.identity(2)

    def render(self):
        pass

    def getCurrentState(self):
        retval = []
        for i in range(self.numStateFrames):
            for j in self.stateWindow[i]:
                retval.append(j)
        return np.array(retval)

    def reset(self):
        self.numSteps = 0
        self.currentHeading = math.pi / 2.0
        self.uuvSpeed = 3.2
        self.steps = 0
        self.cumulativeReward = 0.0
        self.gtLocation = (0.0, 0.0)
        self.estLocation = self.gtLocation
        #self.sensorNoiseStdev = 0.0
        self.destination = (1000.0 * (self.rng1.uniform() - 0.5), 500.0 * self.rng1.uniform() + 500.0)
        self.wcRegionY2 = 100000 #250 + 250 * self.rng1.uniform()
        self.wcRegionY1 = 250 * self.rng1.uniform()
        (x,y) = self.destination
        hypot = math.hypot(x, y)
        ###

        self.gtVelocity = (self.uuvSpeed * x/hypot, self.uuvSpeed * y/hypot)
        self.estVelocity = self.gtVelocity

        self.waterCurrentVector = ((self.rng1.uniform() - 0.5) * 4.0, (self.rng1.uniform() - 0.5) * 4.0)
        currentMagnitude = math.hypot(self.waterCurrentVector[0], self.waterCurrentVector[1])
        randCurrentMagnitude = self.rng1.uniform() * 3.0
        self.waterCurrentVector = (randCurrentMagnitude * self.waterCurrentVector[0] / currentMagnitude, randCurrentMagnitude * self.waterCurrentVector[1] / currentMagnitude)

        self.P = np.identity(2)

        # Reset sliding window of state frames
        # Initialize correctly
        self.stateWindow = self.initStateWindow()
        #stateWindow = Array.fill(numStateFrames)(Array(destination._1/1000.0, destination._2/1000.0, estLocation._1/1000.0, estLocation._2/1000.0, gtVelocity._1, gtVelocity._2)).toList //GFRY
        #state = Array(estVelocity._1, estVelocity._2, gtVelocity._1, gtVelocity._2) //GFRY
        #println(state.toList)
        self.initialDist = math.hypot(self.destination[0], self.destination[1])
        return self.getCurrentState()

    def initStateWindow(self):
        stateArray = []
        desiredHeading = math.atan2(self.destination[1], self.destination[0])
        xVel = math.cos(desiredHeading)
        yVel = math.sin(desiredHeading)
        #stateArray += Array(destination._1/500.0, (destination._2-500.0)/500.0 * 2.0 - 1.0, 0.0, 0.0, xVel/5.2, yVel/5.2)
        stateArray.append([(self.destination[0] - 0.0)/1000.0, (self.destination[1] - 0.0)/1000.0, xVel/5.2, yVel/5.2, 0.0, 0.0])
        prevLocX = 0.0
        prevLocY = 0.0
        for _ in range(1, self.numStateFrames):
            newLocX = prevLocX + xVel
            newLocY = prevLocY + yVel
            #stateArray += Array(destination._1/500.0, (destination._2-500.0)/500.0 * 2.0 - 1.0, newLocX/500.0, (newLocY-500.0)/500.0, xVel/5.2, yVel/5.2)
            stateArray.append([(self.destination[0] - newLocX)/1000.0, (self.destination[1]-newLocY)/1000.0, xVel/5.2, yVel/5.2, 0.0, 0.0])
            prevLocX = newLocX
            prevLocY = newLocY
        self.estLocation = (prevLocX, prevLocY)
        self.gtLocation = self.estLocation
        self.gtVelocity = (xVel, yVel)
        self.estVelocity = self.gtVelocity
        return stateArray

    def step(self, exploreExploitAction):
        prevLocation = self.gtLocation
        (estLocX, estLocY) = self.estLocation
        (destX, destY) = self.destination
        inWaterCurrentRegion = (estLocY >= self.wcRegionY1) and (estLocY <= self.wcRegionY2)
        (cX, cY) = self.waterCurrentVector if (inWaterCurrentRegion and self.uuvSpeed > 0.0) else (0.0, 0.0)
        # biasAndNoise = self.sensorNoiseStdev * rand2.nextGaussian()

        # update GROUND TRUTH vehicle velocity by pointing heading towards destination from ESTIMATED location
        # controls updates UUV heading
        controls = exploreExploitAction
        desiredHeading = math.atan2(destY - estLocY, destX - estLocX) + controls[0] # TODO: type of controls
        self.currentHeading = desiredHeading

        (vX, vY) = (self.uuvSpeed*math.cos(self.currentHeading), self.uuvSpeed*math.sin(self.currentHeading))
        # velocityDiff is for the actuator inputs to the KF
        velocityDiff = (vX - self.estVelocity[0], vY - self.estVelocity[1])
        # add the water current to velocity to simulate sensor values (dvl sensors detect current)
        self.gtVelocity = (vX + cX, vY + cY)
        sensorVx = vX + cX #+ biasAndNoise
        sensorVy = vY + cY #+ biasAndNoise

        # setting up KF inputs
        Zn = np.array([sensorVx, sensorVy])
        Un = np.array([velocityDiff[0], velocityDiff[1]])
        xPrev = np.array([self.estVelocity[0], self.estVelocity[1]])
        pPrev = self.P

        # execute KF (returns list of np.array)
        kfOutput = self.kf(pPrev, xPrev, Zn, Un)
        pNext = kfOutput[1]
        velocityVector = kfOutput[0]

        accel = (velocityVector[0] - self.estVelocity[0], velocityVector[1] - self.estVelocity[1])

        self.estVelocity = (velocityVector[0], velocityVector[1])
        self.estLocation = (self.estLocation[0] + self.estVelocity[0], self.estLocation[1] + self.estVelocity[1])
        self.gtLocation = (self.gtLocation[0] + self.gtVelocity[0], self.gtLocation[1] + self.gtVelocity[1])
        self.P = pNext
        self.state = [
                        (self.destination[0]-self.estLocation[0])/1000.0,
                        (self.destination[1]-self.estLocation[1])/1000.0,
                        sensorVx/5.2,
                        sensorVy/5.2,
                        accel[0]/5.2, #because max wc magnitude in 1 direction is 2
                        accel[1]/5.2
                     ]
        self.steps += 1
        estDist = math.hypot(self.estLocation[0] - self.destination[0], self.estLocation[1] - self.destination[1])
        gtDist = math.hypot(self.gtLocation[0] - self.destination[0], self.gtLocation[1] - self.destination[1])
        isTerminated = self.steps >= self.maxSteps or estDist <= self.threshold

        #rewardLoc1Product = (prevLocation[0]*self.destination[0] + prevLocation[1]*self.destination[1]) / (self.destination[0]*self.destination[0] + self.destination[1]*self.destination[1])
        #rewardLoc2Product = (self.gtLocation[0]*self.destination[0] + self.gtLocation[1]*self.destination[1]) / (self.destination[0]*self.destination[0] + self.destination[1]*self.destination[1])
        #rewardLoc1X = rewardLoc1Product * self.destination[0]
        #rewardLoc1Y = rewardLoc1Product * self.destination[1]
        #rewardLoc2X = rewardLoc2Product * self.destination[0]
        #rewardLoc2Y = rewardLoc2Product * self.destination[1]
        #rewardDiffX = rewardLoc2X - rewardLoc1X
        #rewardDiffY = rewardLoc2Y - rewardLoc1Y
        #sign = np.sign(self.destination[0] * rewardDiffX + self.destination[1] * rewardDiffY)
        #reward = sign * math.hypot(rewardDiffX, rewardDiffY) / self.initialDist
        #reward = -1.0/(self.initialDist/self.uuvSpeed) #* 100.0
        reward = -gtDist/self.initialDist/(self.initialDist/self.uuvSpeed) + 0.002
        self.cumulativeReward += reward
        self.numSteps += 1

        # For chart
        # print("{},{}".format(self.gtLocation[0], self.gtLocation[1]))

        if isTerminated:
            # TODO: save cumulativeReward to results file

            # For Training
            #print("gtDist: {}, controls: {}, steps: {}, episode reward: {}".format(gtDist, controls[0], self.steps, self.cumulativeReward))
            #print("state: {}".format(self.stateWindow[0]))

            # For evaluation
            print("{},{},{},{}".format(controls[0],gtDist, self.steps, self.cumulativeReward/self.numSteps))
            #print("state: {}\n\n".format(self.state))

            #with open(self.resultsFileName, 'a') as f:
            #    f.write("{}\n".format(self.cumulativeReward))
            # For Chart/Training
            #print("\n")

        # Add state to state stateWindow and remove oldest entry
        self.stateWindow.pop(0)
        self.stateWindow.append(self.state)
        return [controls, self.getCurrentState(), reward, isTerminated]

    def kf(self, pPrev, xPrev, Zn, Un):
        H = np.identity(2)
        R = np.array([[self.defaultControls[12], self.defaultControls[13]],
                      [self.defaultControls[14], self.defaultControls[15]]])
        Q = np.array([[self.defaultControls[8], self.defaultControls[9]],
                      [self.defaultControls[10], self.defaultControls[11]]])
        B = np.array([[self.defaultControls[4], self.defaultControls[5]],
                      [self.defaultControls[6], self.defaultControls[7]]])
        A = np.array([[self.defaultControls[0], self.defaultControls[1]],
                      [self.defaultControls[2], self.defaultControls[3]]])

        X_predicted = A.dot(xPrev) + B.dot(Un)
        P_predicted = np.add(A.dot(pPrev).dot(A.transpose()), Q)
        Y_hat = np.subtract(Zn, H.dot(X_predicted))
        S = np.add(H.dot(P_predicted).dot(H.transpose()), R)
        K = P_predicted.dot(H.transpose()).dot(np.linalg.inv(S))
        xNext = np.add(X_predicted, K.dot(Y_hat))
        I = np.identity(H.shape[1])
        pNext = np.subtract(I, K.dot(H)).dot(P_predicted)
        return [xNext, pNext, Y_hat]
