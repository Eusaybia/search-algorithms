# Written by Jack Gardner
# Modified by Rahil Agrawal

import cmd
import subprocess
import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


class Search(cmd.Cmd):

    prompt =    bcolors.OKBLUE + bcolors.BOLD + 'search: ' + bcolors.ENDC
    search_type = "./searchPagerank "

    def default(self, line):
        subprocess.call([self.search_type + line], shell=True)

    def do_open(self, line):
        subprocess.call(["less " + line + ".txt"], shell=True)

    def do_PAGERANK(self, line):
        print (bcolors.WARNING + "Changing search type to pagerank" + bcolors.ENDC)
        self.search_type = "./searchPagerank "

    def do_TFIDF(self, line):
        print (bcolors.WARNING + "Changing search type to pagerank" + bcolors.ENDC)
        self.search_type = "./searchTfIdf "

    def do_exit(self, line):
        subprocess.call(["sh", "clean.sh"])
        exit()


command = ["sh", "update.sh"]
if len(sys.argv) == 2:
    command.append(sys.argv[1])
subprocess.call(command)
Search().cmdloop()
