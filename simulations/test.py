# import inet
# import logging
#
# from inet import *
# #from inet.simulation.cffi import *
#
# logger = logging.getLogger()
# logger.setLevel(logging.INFO)
#
# handler = logging.StreamHandler()
# handler.setFormatter(ColoredLoggingFormatter())
#
# logger.handlers = []
# logger.addHandler(handler)
#
# enable_autoreload()

import csv

with open('all_sensor_data.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        print(', '.join(row))
        
        
        