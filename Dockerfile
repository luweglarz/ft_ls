FROM debian:buster

RUN apt-get update \
&& apt -y install build-essential \
&& apt-get install -y locales

#Build locales to have correct alpha sorting
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen
ENV LC_ALL en_US.UTF-8 

RUN mkdir ft_ls

CMD tail -f /dev/null