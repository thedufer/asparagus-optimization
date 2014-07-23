#!/usr/bin/python
from time import time

letters = "acdegilmnoprstuw"

def hash(str, length):
  h = 7
  for letter in str:
    h = h * 37 + letters.find(letter)
  return h

def unhash(target, length, sofar=""):
  if len(sofar) == length:
    if hash(sofar, length) == target:
      return sofar
  else:
    for letter in letters:
      tmp = unhash(target, length, sofar+letter)
      if tmp is not None:
        return tmp
  return None

print hash("leepadg", 7)
start = time()
print unhash(680131659347L, 7)
print "%f cpu sec" % (time() - start)
