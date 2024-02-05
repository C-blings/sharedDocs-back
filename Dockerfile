FROM debian:latest
COPY . /shareDocs

RUN apt upgrade
RUN apt update
RUN apt install make
RUN TZ=Etc/UTC apt-get -y install tzdata

WORKDIR /shareDocs
RUN make install_deps
RUN dpkg -i libpqxx-7.8_7.8.1-2_amd64.deb
RUN dpkg -i libpqxx-dev_7.8.1-2_amd64.deb

RUN export PATH=$PATH:/usr/lib/postgresql/16/bin
RUN su postgres -c 'pg_ctlcluster start'
RUN su - postgres -c "createdb testDb"


CMD ["make", "all"]
