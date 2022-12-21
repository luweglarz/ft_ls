FROM debian:buster

RUN apt-get update \
&& apt -y install build-essential \
&& apt-get install -y locales \
&& apt -y install valgrind 

#Build locales to have correct alpha sorting


RUN mkdir ft_ls

CMD tail -f /dev/null