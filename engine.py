# Written by Jack Gardner, October 2017
import cmd
import subprocess
import sys

class Search(cmd.Cmd):

    prompt = 'search: '
    search_type = "./searchPagerank "

    def default(self, line):
        subprocess.call([self.search_type + line], shell=True)

    def do_open(self, line):
        subprocess.call(["less " + line + ".txt"], shell=True)

    def do_PAGERANK(self, line):
        print("Changing search type to pagerank")
        self.search_type = "./searchPagerank "

    def do_TFIDF(self, line):
        print("Changing search type to tfidf")
        self.search_type = "./searchTfIdf "

    def do_exit(self, line):
        subprocess.call(["sh", "clean.sh"])
        exit()


subprocess.call(["sh", "update.sh", sys.argv[1]])
subprocess.call(["cat " + "yaggleImage.txt"], shell=True)
print()
Search().cmdloop()
