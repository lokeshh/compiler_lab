print "Given grammar is-"
print "E -> TX"
print "X -> +TX/_"
print "T -> FY"
print "Y -> *FY/_"
print "F -> (E)/i"

global input_string
input_string = raw_input('Enter a string to parse: ')
input_string += '$'
global i
i = 0;
stack = []

def E():
  print ' '*i, 'Trying: E -> TX'
  if T() and X():
    return True
  return False

def T():
  print ' '*i, 'Trying: T -> FY'
  if F() and Y():
    return True

def X():
  global i
  save = i
  if X1():
    return True
  i = save
  if X2():
    return True
  return False

def X1():
  print ' '*i, 'Trying: X -> +TX'
  if check('+') and T() and X():
    return True
  return False

def X2():
  print ' '*i, 'Trying: X -> _'
  return True

def Y():
  global i
  save = i
  if Y1():
    return True
  i = save
  if Y2():
    return True
  return True

def Y1():
  print ' '*i, 'Trying: Y -> *FY'
  return check('*') and F() and Y()

def Y2():
  print ' '*i, 'Trying: Y -> _'
  return True

def F():
  global i
  save = i
  if F1():
    return True
  i = save
  if F2():
    return True
  return False

def F1():
  print ' '*i, 'Trying: F -> (E)'
  return check('(') and E() and check(')')

def F2():
  print ' '*i, 'Trying: F -> i'
  return check('i')

def check(symbol):
  global i
  print ' '*i, 'Trying to match:', input_string[i], symbol
  if input_string[i] == symbol:
    i += 1
    return True
  return False

def start():
  if E():
    if check('$'):
      return True
  return False

print start()