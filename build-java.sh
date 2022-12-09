modulePath="/usr/share/openjfx/lib"

declare -a javafxModules=(
    "javafx.base"
    "javafx.graphics"
    "javafx.media"
    )
javaClasspath=""
for val in ${javafxModules[@]}; do
  javaClasspath="$val;$javaClasspath"
done
addModules=""
for val in ${javafxModules[@]}; do
  addModules="$val.jar;$addModules"
done
# java --module-path /usr/share/openjfx/lib --add-modules javafx.base,javafx.graphics,javafx.media -classpath "com.nana;/usr/share/openjfx/lib/javafx.graphics.jar" ./com/nana/uLCDInterface.java
javac --module-path $modulePath --add-modules $addModules -classpath "com.nana;$javaClasspath" ./com/nana/uLCDInterface.java