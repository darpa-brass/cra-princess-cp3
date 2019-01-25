#!/bin/sh
set -x -e
UID=$(id -u)

if [ -n "$HTTP_PROXY" ]; then 
  BUILD_ARGS="$BUILD_ARGS --build-arg http_proxy=$HTTP_PROXY --build-arg HTTP_PROXY=$HTTP_PROXY"
  RUN_ARGS="$RUN_ARGS --env http_proxy=$HTTP_PROXY --env HTTP_PROXY=$HTTP_PROXY"
  JAVA_OPTS="$JAVA_OPTS -Dhttp.proxyHost=llproxy.llan.ll.mit.edu -Dhttp.proxyPort=8080"
fi
if [ -n "$HTTPS_PROXY" ]; then
  BUILD_ARGS="$BUILD_ARGS --build-arg https_proxy=$HTTPS_PROXY --build-arg HTTPS_PROXY=$HTTPS_PROXY"
  RUN_ARGS="$RUN_ARGS --env https_proxy=$HTTPS_PROXY --env HTTPS_PROXY=$HTTPS_PROXY"
  JAVA_OPTS="$JAVA_OPTS -Dhttps.proxyHost=llproxy.llan.ll.mit.edu -Dhttps.proxyPort=8080"
fi
if [ -n "$JAVA_OPTS" ]; then
  JAVA_OPTS="--env JAVA_OPTS=\"${JAVA_OPTS}\""
fi

docker build ${BUILD_ARGS} -t cra/sbt -f Dockerfile.sbt .

mkdir -p $PWD/sbt-home

eval $(echo "docker run -u $UID -v $PWD/../:/build/ --workdir /build/release -v $PWD/sbt-home:/home/$USER --env HOME=/home/$USER --env SBT_OPTS=-Duser.home=/home/$USER ${RUN_ARGS} ${JAVA_OPTS} cra/sbt:latest /bin/sh -c 'find /build -type f -name \"*.sh\" -exec chmod +x {} \; && ./ll-release.sh'")

cd ../releases/princess-cp1_*
docker build ${BUILD_ARGS} -t cra/sut-cp1 .
cd -

cd ../releases/princess-cp2_*/cp2/
docker build ${BUILD_ARGS} -t cra/sut-cp2 .
cd -

cd ../releases/princess-cp3_*
docker build ${BUILD_ARGS} -t cra/sut-cp3 .
cd -

cd ../releases/princess-cp3-phase3_*
docker build ${BUILD_ARGS} -t cra/sut-cp3-p3 .
cd -
