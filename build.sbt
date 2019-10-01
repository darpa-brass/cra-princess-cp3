import sbt._
import Keys._
import sbt.Package.ManifestAttributes

name := "princess-root"

lazy val princessSettings = Seq(
  organization := "com.cra.princess",
  description := "PRINCESS: Probabilistic Representation of Intent Commitments to Ensure Software Survival",
  scalaVersion := "2.12.8",
  crossPaths := true,
  publishMavenStyle := true,
  scalacOptions ++= Seq("-feature", "-language:existentials", "-deprecation", "-language:postfixOps"),
  scalacOptions in(Compile, doc) += "-no-java-comments",
  javacOptions in(Compile, compile) ++= Seq("-source", "1.8", "-target", "1.8"),
  javaOptions in(Compile, compile) += "-Xmx4G",
  updateOptions := updateOptions.value.withCachedResolution(true),
  // Copy all managed dependencies to \lib_managed directory
  retrieveManaged := true,
  // Enable forking
  fork := false,
  packageOptions := Seq(ManifestAttributes(
    ("Bundle-RequiredExecutionEnvironment", "JavaSE-1.8")
  )),
  pomExtra :=
    <url>http://www.github.com/p2t2/figaro</url>
      <developers>
        <developer>
          <name>Avrom J. Pfeffer</name>
          <email>apfeffer@cra.com</email>
          <organization>Charles River Analytics Inc.</organization>
          <organizationUrl>http://www.cra.com</organizationUrl>
        </developer>
      </developers>
      <developers>
        <developer>
          <name>Curt Wu</name>
          <email>cwu@cra.com</email>
          <organization>Charles River Analytics Inc.</organization>
          <organizationUrl>http://www.cra.com</organizationUrl>
        </developer>
      </developers>
      <licenses>
        <license>
          <name>Figaro License</name>
          <url>https://github.com/p2t2/figaro/blob/master/LICENSE</url>
        </license>
      </licenses>
      <scm>
        <connection>scm:git:git@github.com:p2t2/figaro.git</connection>
        <developerConnection>scm:git:git@github.com:p2t2/figaro.git</developerConnection>
        <url>git@github.com:p2t2/figaro.git</url>
      </scm>
)

lazy val scalaMajorMinor = "2.12"

lazy val root = (project in file("."))
  .settings(princessSettings)
  .settings(publishLocal := {})
  .settings(publish := {})
  .dependsOn(princess, kalmanfilter, localizationalgorithm, remus, evaluation, kalmanfiltercomponent, remusclient, mockwebservice, remusviewer, pathplanner, training)
  .aggregate(princess, kalmanfilter, localizationalgorithm, remus, evaluation, kalmanfiltercomponent, remusclient, mockwebservice, remusviewer, pathplanner, training)

lazy val princess = (project in file("princess"))
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "com.cra.figaro" %% "figaro" % "5.0.0.0",
    "edu.illinois.wala" %% "walafacade" % "0.2",
    "asm" % "asm-all" % "3.3.1",
    "org.apache.commons" % "commons-math3" % "3.3",
    "nz.ac.waikato.cms.weka" % "weka-dev" % "3.7.12",
    "log4j" % "log4j" % "1.2.17",
    "org.slf4j" % "slf4j-api" % "1.7.21",
    "org.slf4j" % "slf4j-log4j12" % "1.7.21",
    "com.storm-enroute" %% "scalameter" % "0.8.2" exclude("org.ow2.asm", "asm"),
    "org.jgrapht" % "jgrapht-jdk1.5" % "0.7.3",
    "org.scala-graph" %% "graph-core" % "1.11.4",
    "org.scalatest" %% "scalatest" % "3.0.2" % "test",
    "junit" % "junit" % "4.12" % "test",
    "fr.inria.gforge.spoon" % "spoon-core" % "5.9.0",
    "org.deeplearning4j" % "deeplearning4j-core"% "1.0.0-beta3",
    "org.deeplearning4j" % "deeplearning4j-zoo" % "1.0.0-beta3",
    "org.deeplearning4j" % "deeplearning4j-modelimport" % "1.0.0-beta3",
    "org.deeplearning4j" % "rl4j-core" % "1.0.0-beta3",
    "org.nd4j" % "nd4j-native-platform" % "1.0.0-beta3",
    "org.datavec" % "datavec-api" % "1.0.0-beta3",
    "org.deeplearning4j" % "rl4j-core" % "1.0.0-beta3",
    "com.typesafe.play" %% "play-json" % "2.7.4"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val training = (project in file("training"))
  .dependsOn(princess, kalmanfilter)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "org.apache.commons" % "commons-math3" % "3.3",
    "log4j" % "log4j" % "1.2.17",
    "com.storm-enroute" %% "scalameter" % "0.8.2" exclude("org.ow2.asm", "asm"),
    "org.scalatest" %% "scalatest" % "3.0.2" % "test",
    "junit" % "junit" % "4.12" % "test"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
// SBTEclipse settings

lazy val kalmanfilter = (project in file("kalmanfilter"))
  .dependsOn(localizationalgorithm, princess)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "org.apache.commons" % "commons-math3" % "3.3",
    "log4j" % "log4j" % "1.2.17",
    "com.storm-enroute" %% "scalameter" % "0.8.2" exclude("org.ow2.asm", "asm"),
    "com.zenecture" % "neuroflow-core_2.12" % "1.2.5",
    "com.zenecture" % "neuroflow-application_2.12" % "1.2.5",
    "org.scalatest" %% "scalatest" % "3.0.2" % "test",
    "junit" % "junit" % "4.12" % "test"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val localizationalgorithm = (project in file("localizationalgorithm"))
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "com.cra.figaro" %% "figaro" % "5.0.0.0",
    "org.apache.commons" % "commons-math3" % "3.3",
    "org.jfree" % "jfreechart" % "1.0.19",
    "org.pentaho.pentaho-commons" % "pentaho-package-manager" % "1.0.8",
    "nz.ac.waikato.cms.weka" % "weka-dev" % "3.7.12",
    "com.github.yannrichet" % "JMathPlot" % "1.0.1",
    "log4j" % "log4j" % "1.2.17",
    "com.storm-enroute" %% "scalameter" % "0.8.2" exclude("org.ow2.asm", "asm"),
    "org.jgrapht" % "jgrapht-jdk1.5" % "0.7.3",
    "org.scalatest" %% "scalatest" % "3.0.2" % "test",
    "junit" % "junit" % "4.12" % "test",
    "com.google.guava" % "guava" % "20.0"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val kalmanfiltercomponent = (project in file("kalmanfilter-component"))
  .dependsOn(princess, kalmanfilter, remus, evaluation)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "org.yaml" % "snakeyaml" % "1.17",
    "log4j" % "log4j" % "1.2.17"
  ))
  .settings(version := "1.0.0")
  .settings(retrieveManaged := true)
  .settings(unmanagedBase := baseDirectory.value / "target-platform")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx8G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val remusclient = (project in file("remus-client"))
  .dependsOn(kalmanfiltercomponent, princess, kalmanfilter, localizationalgorithm, remus, evaluation, pathplanner, training)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "org.apache.activemq" % "activemq-client" % "5.14.0",
    "log4j" % "log4j" % "1.2.17",
    "org.scalatest" %% "scalatest" % "3.0.2" % "test"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx8G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  .settings(javaOptions in(Test, run) += "-Djava.library.path=octave-bridge/src")
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))
  // Set the Main-Class attribute
  .settings(mainClass in Compile := Some("com.cra.princess.remusclient.legacy.RemusClient"))

lazy val pathplanner = (project in file("pathplanner"))
  .dependsOn(princess, evaluation)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "log4j" % "log4j" % "1.2.17",
    "junit" % "junit" % "4.12" % "test",
    "com.novocode" % "junit-interface" % "0.11" % "test",
    "com.zenecture" % "neuroflow-core_2.12" % "1.2.5",
    "com.zenecture" % "neuroflow-application_2.12" % "1.2.5"
  ))
  .settings(version := "1.0.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(concurrentRestrictions in Global += Tags.limit(Tags.Test, 1))
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

// ***** Challenge Problem Tookit Projects *****

lazy val evaluation = (project in file("cptoolkit/source/evaluation"))
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "org.scalatest" %% "scalatest" % "3.0.2" % "test",
    "junit" % "junit" % "4.12" % "test",
    "com.novocode" % "junit-interface" % "0.11" % "test",
    "net.liftweb" %% "lift-json" % "3.2.0"
  ))
  .settings(version := "1.3.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(concurrentRestrictions in Global += Tags.limit(Tags.Test, 1))
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val remus = (project in file("cptoolkit/source/remus"))
  .dependsOn(evaluation)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "junit" % "junit" % "4.12" % "test",
    "com.novocode" % "junit-interface" % "0.11" % "test",
    "net.liftweb" %% "lift-json" % "3.2.0"
  ))
  .settings(version := "1.3.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(concurrentRestrictions in Global += Tags.limit(Tags.Test, 1))
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val mockwebservice = (project in file("cptoolkit/source/mockwebservice"))
  .dependsOn(evaluation)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "log4j" % "log4j" % "1.2.17",
    "junit" % "junit" % "4.12" % "test",
    "com.novocode" % "junit-interface" % "0.11" % "test"
  ))
  .settings(version := "1.3.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx8G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // ScalaMeter settings
  .settings(testFrameworks += new TestFramework("org.scalameter.ScalaMeterFramework"))
  .settings(logBuffered := false)
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))

lazy val remusviewer = (project in file("cptoolkit/source/remus-viewer"))
  .dependsOn(remus)
  .settings(princessSettings)
  .settings(libraryDependencies ++= Seq(
    "junit" % "junit" % "4.12" % "test",
    "com.novocode" % "junit-interface" % "0.11" % "test",
    "net.liftweb" %% "lift-json" % "3.2.0"
  ))
  .settings(version := "1.3.0")
  // Increase max memory for JVM for both testing and runtime
  .settings(javaOptions in(Test, run) += "-Xmx6G")
  // test settings
  .settings(parallelExecution in Test := false)
  .settings(concurrentRestrictions in Global += Tags.limit(Tags.Test, 1))
  .settings(testOptions in Test += Tests.Argument("-oD"))
  // SBTEclipse settings
  .settings(EclipseKeys.eclipseOutput := Some("target/classes"))
