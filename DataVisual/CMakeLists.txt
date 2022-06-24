project(datavisual)

add_custom_target(datavisual
COMMAND npm run cmake -d ./cplugin
COMMAND npm build
)