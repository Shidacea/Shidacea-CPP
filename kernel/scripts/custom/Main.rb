# The absolute main file
# Everything starts here

SDC::Script.path = "demo_projects/Example_Test"

config = SDC::Launshi.load_config_file("config.json")
SDC::Launshi.load_scripts(config)