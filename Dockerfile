FROM debian:latest
RUN apt upgrade
RUN apt update
RUN apt install make
RUN TZ=Etc/UTC apt-get -y install tzdata
COPY ./Makefile .
COPY libpqxx-7.8_7.8.1-2_amd64.deb .
COPY libpqxx-dev_7.8.1-2_amd64.deb .
RUN make install_deps
RUN dpkg -i libpqxx-7.8_7.8.1-2_amd64.deb
RUN dpkg -i libpqxx-dev_7.8.1-2_amd64.deb

EXPOSE 80

WORKDIR /shareDocs
COPY . .

CMD make all
