#!/usr/bin/env python

import sys
import DAL

def createTest():
  f = DAL.CLA_File('test-reopen-rw-cla-py.h5', DAL.CLA_File.CREATE)

  f.clockFrequency().value = 160.0

def reopenrwTest():
  f = DAL.CLA_File('test-reopen-rw-cla-py.h5', DAL.CLA_File.READWRITE)

  f.clockFrequencyUnit().value = 'MHz'

def checkTest():
  err = 0

  f = DAL.CLA_File('test-reopen-rw-cla-py.h5')

  if f.clockFrequency().get() != 160.0:
    err = 1
    print 'Written clock freq val could not be read back'
  if f.clockFrequencyUnit().get() != 'MHz':
    err = 1
    print 'Written clock freq unit val could not be read back'

  return err

def main():
  createTest()
  reopenrwTest()

  return checkTest()

if __name__ == '__main__':
  sys.exit(main())

