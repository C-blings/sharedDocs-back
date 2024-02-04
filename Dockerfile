FROM ubuntu:latest
COPY . /shareDocs

RUN apt upgrade
RUN apt update
RUN apt install make
RUN DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get -y install tzdata

WORKDIR /shareDocs

RUN make install_deps

CMD ["make", "test"]