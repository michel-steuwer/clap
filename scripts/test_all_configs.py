#!/usr/bin/python
import itertools as it
import subprocess as sp
import os,sys,getopt

def main(argv):
  options={
    'CMAKE_CXX_COMPILER':[
      '/home/s0841430/local/bin/g++','/home/s0841430/llvm/trunk_recent/bin/clang++'
    ],
    'DEBUG_TRACK_OVERHEAD':['ON','OFF'],
    'TRACK_API_CALLS':['ON','OFF'],
    'TRACK_EVENTS':['ON','OFF'],
    'TRACK_REFCOUNT':['ON','OFF']
    } 

  try:
      opts, args = getopt.getopt(argv,"a,[abort_on_error]")
  except getopt.GetoptError:
      print 'build.py -a'
      sys.exit(2)
  error_abort = None
  for opt, arg in opts:
    if opt in ("-a", "--abort_on_error"):
      error_abort = True

  combinations = [' '.join(['-D%s=%s' % p for p in zip(options, prod)]) 
      for prod in it.product(*(options[varName] for varName in options))]

  counter = 1
  for optionset in combinations:
    print '[' + str(counter) + '/' + str(len(combinations)) + '] Testing build with options ' + optionset
    command = 'cmake ' + optionset + ' . && make -j6'
    ret = sp.call(command, shell=True)  
    if ret != 0:
      print 'build failed for: ' + optionset
      if error_abort:
        return -1
    else:
      counter += 1

if __name__ == "__main__":
   sys.exit(main(sys.argv[1:]))
