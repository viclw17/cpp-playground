# A simple database
# A dictionary with person names as keys. Each person is represented as
# another dictionary with the keys 'phone' and 'addr' referring to their phone 
# number and address, respectively.

people = { # dictionary, person names as key, person's info as value
    'Alice' : { # dictionary
        'phone' : '1234',
        'addr' : 'Foo drive 23'
    },
    'Beth' : {
        'phone' : '2323',
        'addr' : 'Bar street 42'
    },
    'Cecil' : {
        'phone' : '4545',
        'addr' : 'Baz avenue 90'
    }
}

# Descriptive labels for the phone number and address, used for printing
labels = {'phone' : 'phone number', 'addr' : 'address'}

name = raw_input('Name: ')
request = raw_input('Phone number (p) or address (a)? ')

# Use the correct key:
if request == 'p' : key = 'phone'
if request == 'a' : key = 'addr'

if name in people : print "%s's %s is %s." % (name, labels[key], people[name][key])
else: print "%s does not exist in the database." % name

import pprint as pp
pp.pprint(people)
#print '\n'
#print people
