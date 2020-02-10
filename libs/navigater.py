import os
import os.path

home_folder = os.path.abspath(".")
handle_map = {}


def handle(key, path):
    global handle_map
    assert isinstance(path, str), "Path must be a string!"

    handle_map[key] = os.path.abspath(path)

def get_in(folder):
    global home_folder

    home_folder = os.path.join(home_folder, folder)

def go_up():
    global home_folder

    home_folder = os.path.basename(home_folder)

def get_path(key):
    global home_folder
    global handle_map

    return os.path.relpath(handle_map[key], start=home_folder)
