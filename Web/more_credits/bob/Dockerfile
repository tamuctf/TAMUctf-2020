FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install wget vim firefox python3-pip -y

# install geckodriver
RUN wget https://github.com/mozilla/geckodriver/releases/download/v0.26.0/geckodriver-v0.26.0-linux64.tar.gz
RUN tar xvfz geckodriver-v0.26.0-linux64.tar.gz
RUN mv geckodriver /usr/local/bin

# upgrade pip
RUN pip3 install --upgrade pip

# install selenium
RUN pip3 install selenium

COPY bob_script.py .

ENTRYPOINT ["python3", "/bob_script.py"]
