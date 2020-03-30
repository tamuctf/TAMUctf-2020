from selenium import webdriver
from selenium.webdriver.firefox.options import Options
import time

WEB_URL = 'http://172.17.0.2'

def main():
    print('Setting up browser...', end='')
    options = Options()
    options.set_headless(headless=True)
    browser = webdriver.Firefox(firefox_options=options)
    print('done')
    username = 'bob'
    password = 'yG_hn6@@BJhw3H=5'
    while True:
        start = time.time()
        try:
            print('Logging in...', end='')
            browser.get(WEB_URL + '/login')
            browser.find_element_by_id('user').send_keys(username)
            browser.find_element_by_id('pass').send_keys(password)
            browser.find_element_by_id('login_submit').click()
            print('done')
        except Exception as e:
            print(e)
        print(start)
        while True:
            time.sleep(5)
            print('Refreshing page...', end='')
            try:
                browser.get(WEB_URL + '/gift')
            except Exception as e:
                print(e)
            print('done')
            if('/login' in browser.current_url):
                break
    browser.quit()

if __name__=='__main__':
    main()
