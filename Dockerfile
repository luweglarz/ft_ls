FROM debian:buster

RUN apt-get update \
&& apt -y install build-essential \
&& apt-get install -y locales

RUN sed -i '/fr_FR.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

ENV LC_ALL fr_FR.UTF-8  

RUN mkdir ft_ls

CMD tail -f /dev/null