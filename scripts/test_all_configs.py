#!/usr/bin/python3.3
# Quick script to plough through all config options
import itertools as it
import subprocess as sp
import os,sys,getopt,time
import tempfile
import shutil
import concurrent.futures

class BuildInfo:
  config = ''
  time = 0
  ret = 0
  def __init__(self, conf=None):
    self.config = conf

def build(info,threaded,path):
  prefix = ''
  if threaded:
    prefix = 'INPLACE_HEADERS'
    dirpath = tempfile.mkdtemp()
    os.chdir(dirpath)
  command = 'cmake ' + prefix + ' ' + info.config + ' ' + path + ' && make -j4'
  ts = time.time()
  info.ret = sp.call(command, shell=True)
  info.time = time.time() - ts
  if info.ret != 0:
    print('build failed for: ' + info.config)
  if threaded:
    shutil.rmtree(dirpath)
  return info

def main(argv):
  # dictionary of all options
  options={
    'CMAKE_CXX_COMPILER':[
    '/scratch/s0841430/compilers/gcc-4.9.2/bin/g++',
    '/scratch/s0841430/compilers/gcc-4.8.4/bin/g++',
    #'/scratch/s0841430/compilers/gcc-4.7.4/bin/g++',
    #'/scratch/s0841430/compilers/gcc-4.6.4/bin/g++',
    #'/scratch/s0841430/compilers/gcc-4.5.4/bin/g++',
    #'/scratch/s0841430/compilers/clang-3.0/bin/clang++',
    #'/scratch/s0841430/compilers/clang-3.1/bin/clang++',
    #'/scratch/s0841430/compilers/clang-3.2/bin/clang++',
    #'/scratch/s0841430/compilers/clang-3.3/bin/clang++',
    '/scratch/s0841430/compilers/clang-3.4.2/bin/clang++',
    '/scratch/s0841430/compilers/clang-3.5.2/bin/clang++'
    ],
    'OPENCL_VERSION':[
      '1.0','1.1','1.2','2.0'
    ],
    'OPENCL_ALLOW_DEPRECATED':['ON','OFF'],
    'DEBUG_TRACK_OVERHEAD':['ON','OFF'],
    'TRACK_API_CALLS':['ON','OFF'],
    'TRACK_EVENTS':['ON','OFF'],
    'TRACK_REFCOUNT':['ON','OFF'],
    'TRACK_KERNEL_ARGUMENTS':['ON','OFF'],
    'TRACK_PROGRAMS':['ON','OFF']
    } 

  # option parsing
  try:
     opts, args = getopt.getopt(argv,"atp:,[abort_on_error,threaded,path:]")
  except getopt.GetoptError:
      print('build.py -a')
      sys.exit(2)

  error_abort = None
  threaded = False
  path = '.'

  for opt, arg in opts:
    if opt in ("-a", "--abort_on_error"):
      error_abort = True
    if opt in ("-t", "--threaded"): 
      threaded = True
    if opt in ("-p", "--path"):
      path = arg
  print('path is : ' + path)

  # generate all combinations
  keylist = sorted(options.keys())
  combinations = [' '.join(['-D%s=%s' % p for p in zip(keylist, prod)]) 
      for prod in it.product(*(options[varName] for varName in keylist))]
  infos = [BuildInfo(optionset) for optionset in combinations]

  print('Testing ' + str(len(combinations)) + ' combinations')

  # build all configs
  if threaded:
    executor = concurrent.futures.ProcessPoolExecutor(max_workers=36)
    futures = [executor.submit(build,info,threaded,path) for info in infos]
    concurrent.futures.wait(futures)
    infos = [future.result() for future in futures]
  else:
    for info in infos:
      if build(info,threaded,path).ret != 0:
        if error_abort:
          print('Build failed for ' + info.config)
          sys.exit(-1)

  passed = 0
  for info in infos:
    print('conf: ' + info.config)
    print('time: ' + str(info.time))
    if info.ret != 0:
      print('!!! Config failed')
    else:
      print('config: ok')
      passed += 1
    print('')
  print('[' + str(passed) + '/' + str(len(infos)) + '] passed')


if __name__ == "__main__":
   sys.exit(main(sys.argv[1:]))
