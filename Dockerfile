FROM debian:buster

RUN apt-get update \
&& apt -y install build-essential

RUN mkdir ft_ls

CMD tail -f /dev/null