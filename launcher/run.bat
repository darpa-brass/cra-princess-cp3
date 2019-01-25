set "MYPROPS=-Dlog4j.debug=false -Dlog4j.configuration=file:log4j.properties -Djava.library.path=.\lib -cp .;.\lib\*;..\lib\*"

echo %MYPROPS%

java -ea %MYPROPS% com.cra.princess.remusclient.RemusClient
