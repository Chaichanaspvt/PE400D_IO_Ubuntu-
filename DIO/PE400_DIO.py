#!/usr/bin/python
from subprocess import call
import logging
import logging.handlers as handlers
import os
class PE400_DIO:
    def __init__(self,passwords = None,interval=100):
        """
           This Class use for PE400D from ASUS \n 
           create objects by SP Vision[CHAICHANA]  \n
           for support Minebea  \n
           passwords is passwords 's root if you not set passwords  \n
           you must to use sudo python
        """
        #Create Log
        self.logger = logging.getLogger('PE400_DIO')
        self.logger.setLevel(logging.INFO)
        #Here we create a our formatter
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        # Create a Handler for logging events
    
        if not os.path.exists('bin/Log'):
            os.makedirs('bin/Log')

        logHandler = handlers.TimedRotatingFileHandler('bin/Log/DIO_SP.log',
         when='S', interval=100, backupCount=100)
        logHandler.setLevel(logging.INFO)
        # Set Level for logging events 
        logHandler.setFormatter(formatter)
        self.logger.addHandler(logHandler)
        self.logger.info('Created logger')

        
        self.passwords = passwords
        self.interval = int(interval)
        # DI Input 0 or 1
        self._DI0_status = 99
        self._DI1_status = 99
        self._DI2_status = 99
        self._DI3_status = 99
        # DO Output 0 or 1
        self._DO0_status = 99
        self._DO1_status = 99
        self._DO2_status = 99
        self._DO3_status = 99
        self._init_DIO()

        #Check status of DIO
    def _init_DIO(self):
        self._DO0()
        self._DO1()
        self._DO2()
        self._DO3()
        self._DI0()
        self._DI1()
        self._DI2()
        self._DI3()
     

#region DO(Output)  
    def _DO0(self,status = 0):
        try:
            if status == 0 or status == 1:
               self._DO0_status = call(["./bin/DO0 {}".format(status)],shell=True)
        except Exception as e:
                self._DO0_status = 99
                self.logger.error(str(e))
        return self._DO0_status
    def _DO1(self,status = 0):
        try:
            if status == 0 or status == 1:
                self._DO1_status = call(["./bin/DO1 {}".format(status)],shell=True)
        except Exception as e:
                self._DO1_status = 99
                self.logger.error(str(e))
        return self._DO1_status
    def _DO2(self,status = 0):
        try:
            if status == 0 or status == 1:
                self._DO2_status = call(["./bin/DO2 {}".format(status)],shell=True)
        except Exception as e:
                self._DO2_status = 99
                self.logger.error(str(e))
        return self._DO2_status
    def _DO3(self,status = 0):
        try:
            if status == 0 or status == 1:
               self._DO3_status = call(["./bin/DO3 {}".format(status)],shell=True)
        except Exception as e:
                self._DO3_status = 99
                self.logger.error(str(e))
        return self._DO3_status
#endregion
#region DI(Input)      
    def _DI0(self):
        try:
               self._DI0_status = call("./bin/DI0")
               return self._DI0_status  
        except Exception as e:
                self._DI0_status =99
                self.logger.error(str(e))
                return self._DI0_status
    def _DI1(self):
        try:
               self._DI1_status = call("./bin/DI1")
               return self._DI1_status  
        except Exception as e:
                self._DI1_status  = 99
                self.logger.error(str(e))
                return self._DI1_status
    def _DI2(self):
        try:
               self._DI2_status = call("./bin/DI2")
               return self._DI2_status  
        except Exception as e:
                self._DI2_status  = 99
                self.logger.error(str(e))
                return self._DI2_status
    def _DI3(self):
        try:
               self._DI3_status = call("./bin/DI3")
               return self._DI3_status  
        except Exception as e:
                self._DI3_status  = 99
                self.logger.error(str(e))
                return self._DI3_status
    
#endregion
