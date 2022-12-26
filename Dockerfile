FROM debian:buster

RUN apt-get update \
&& apt -y install build-essential \
&& apt-get install -y locales \
&& apt -y install valgrind 

RUN mkdir ft_ls

CMD tail -f /dev/null