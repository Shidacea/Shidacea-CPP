# The absolute main file
# Everything starts here

main_routine(SDC::Launshi::SceneLaunshi, 'Shidacea - Launshi', 1280, 720)

SDC::Data.clear_containers

SDC::Script.path = SDC::Launshi.get_config.path

SDC::Launshi.load_scripts(SDC::Launshi.get_config)