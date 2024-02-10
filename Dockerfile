FROM debian:latest
RUN apt upgrade
RUN apt update
RUN apt install make
RUN TZ=Etc/UTC apt-get -y install tzdata
COPY ./Makefile .
COPY ./external_libs/*.deb ./
RUN make install_deps
RUN dpkg -i *.deb

EXPOSE 80

WORKDIR /shareDocs
COPY . .

CMD make all
