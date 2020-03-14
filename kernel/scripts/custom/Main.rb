# The absolute main file
# Everything starts here

main_routine(SDC::Launshi::SceneLaunshi, 'Shidacea - Launshi', 1280, 720)

SDC::Script.path = "demo_projects/Example_Test"

config = SDC::Launshi.load_config_file("config.json")

SDC::Data.clear_containers

SDC::Launshi.load_scripts(config)