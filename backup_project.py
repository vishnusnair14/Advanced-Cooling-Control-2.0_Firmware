# backup_project.py

# [Part of ADVANCED COOLING CONTROL ALGORITHM]

''' Python code for backup, vscode current workspace directory 
	  this code will backup all the folder and subfolder of current
	  file's directory. Paste this script to the directory whose
	  content wants to be backuped '''

# [vishnus_technologies (C) 2022]
# ---------------------------------------------------------------


import os
import shutil

_usrname = os.getenv('USERNAME')

# DIR CONSTANTS:
_usr = f"C:/Users/{_usrname}/"
_doc = f"{_usr}/Documents/"
_dstp = f"{_usr}/Desktop/"
_dwnd = f"{_usr}/Downloads/"

src = os.path.dirname(os.path.realpath(__file__))
def_dst = "D:/project_backup_vscode/"

# one-line message allowed
_msg = "\nPython program for project backup (AdvCoolingControl)"
print(_msg)
for i in range(len(_msg)-1):
  print("-", end="")
dst = input("\nEnter the destination directory: ")

if(len(dst) == 0):
	print("[MSG: You have entered nothing, setting this directory\n      {" +def_dst+"} as default destination folder]\n")
else:
  if(os.path.exists(dst)):
    print("Directory entered: "+dst+" is validated")
    shutil.copytree(src, dst)
  else: print("[ERROR: You have entered invalid destination directory!]\n")

