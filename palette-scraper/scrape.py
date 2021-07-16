from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

import urllib
import time
import random


PATH = "C:\Webdrivers\chromedriver.exe"
preUrl = "https://unsplash.com/s/photos/" 

# search setup
search_term = input("Please enter a search term\n")
img_folder = "Assets"

driver = webdriver.Chrome(PATH)
driver.get("https://unsplash.com/")

# image search conducted 
search = driver.find_element_by_name("searchKeyword")
search.send_keys(search_term)
search.send_keys(Keys.RETURN)

# checks for valid search and downloads first image (make it download a random one)
try:
    image = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.CLASS_NAME, "_2UpQX"))
    )
    image.click()
    
except:
    print("error-closing now")
    driver.quit()
webdriver.send_keys(Keys.LEFT)
next1 = driver.find_element_by_class_name("QTFfk _2y61C")
next1.click()
download = driver.find_element_by_class_name("_2Aga-")
#download.click()

time.sleep(5)
print(driver.title)
driver.quit()
