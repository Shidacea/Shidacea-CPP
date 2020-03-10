# The absolute main file
# Everything starts here

main_routine(SceneMain, 'My Shidacea Project', 1280, 720)

SDC::Script.path = "demo_projects/Example_Test"

SDC::Script.load_recursively("scripts/custom/resources")
SDC::Script.load_recursively("scripts/custom/scenes")
SDC::Script.load_recursively("scripts/custom/entities")
SDC::Script.load_recursively("scripts/custom/other")
SDC::Script.load("scripts/custom/Game.rb")
SDC::Script.load("scripts/custom/Main.rb")