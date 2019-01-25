addSbtPlugin("com.typesafe.sbteclipse" % "sbteclipse-plugin" % "5.1.0")

addSbtPlugin("org.scoverage" % "sbt-scoverage" % "1.3.5"  % "provided")

addSbtPlugin("net.virtual-void" % "sbt-dependency-graph" % "0.8.2")

resolvers += Classpaths.sbtPluginReleases
resolvers += "Central Maven 2 Repo" at "http://central.maven.org/maven2"
