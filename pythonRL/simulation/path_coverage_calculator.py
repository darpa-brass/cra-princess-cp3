import math
from simulation.SearchAreaGrid import SearchAreaGrid
from simulation.Point import Point
import path_planner


class path_coverage_calculator(object):
    def __init__(self, plan, search_p1, search_p2, altitude, fov_radians):
        self.view_size = 2.0 * altitude * math.tan(fov_radians / 2.0)
        self.plan = plan
        self.search_grid = SearchAreaGrid(Point(search_p1[0], search_p1[1]),
                                          Point(search_p2[0], search_p2[1]), self.view_size)

    def interpolate(self):
        i = 0
        j = 1
        # calculate if slope is defined
        while self.plan[i][0] < path_planner.END_MARKER and math.isfinite(self.plan[i][0]) and \
                self.plan[i][1] < path_planner.END_MARKER and math.isfinite(self.plan[i][1]) and \
                self.plan[j][0] < path_planner.END_MARKER and math.isfinite(self.plan[j][0]) and \
                self.plan[j][1] < path_planner.END_MARKER and math.isfinite(self.plan[j][1]):
            slope = None
            if self.plan[j][0] - self.plan[i][0] > 0.0:
                slope = (self.plan[j][1] - self.plan[i][1]) / (self.plan[j][0] - self.plan[i][0])
            start_point = Point(self.plan[i][0], self.plan[i][1])  # first point in leg
            end_point = Point(self.plan[j][0], self.plan[j][1])  # last point in leg
            self.search_grid.visit(start_point)
            leg_size = end_point.distance(start_point)
            interp_distance = self.search_grid.cell_size / 4.0

            # Calculate x and y increment for each point interior to leg (each point separated by viewSize/2.0)
            x_increment = math.sqrt(math.pow(interp_distance, 2)/(1.0 + slope * slope)) if slope is not None else 0.0
            y_increment = math.fabs(slope) * x_increment if slope is not None else interp_distance

            if self.plan[i][0] > self.plan[j][0]:
                x_increment *= -1.0

            if self.plan[i][1] > self.plan[j][1]:
                y_increment *= -1.0

            # calculate number of interior leg points
            num_leg_pts = int(math.floor(leg_size/interp_distance))
            cur_point = start_point

            for k in range(0, num_leg_pts):
                next_point = Point(cur_point.x + x_increment, cur_point.y + y_increment)
                self.search_grid.visit(next_point)
                cur_point = next_point
            self.search_grid.visit(end_point)
            i += 1
            j += 1

    def coverage(self):
        self.interpolate()
        return self.search_grid.get_coverage()


if __name__ == '__main__':
    pass
