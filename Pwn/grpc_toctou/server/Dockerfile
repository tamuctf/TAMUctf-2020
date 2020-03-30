# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM i386/debian:stretch

RUN apt-get update && apt-get install -y \
  build-essential autoconf git pkg-config \
  automake libtool curl make g++ unzip \
  && apt-get clean

# install protobuf first, then grpc
ENV GRPC_RELEASE_TAG v1.10.x
RUN git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc /var/local/git/grpc && \
		cd /var/local/git/grpc && \
    git submodule update --init && \
    echo "--- installing protobuf ---" && \
    cd third_party/protobuf && \
    ./autogen.sh && ./configure --enable-shared && \
    make -j$(nproc) && make -j$(nproc) check && make install && make clean && ldconfig && \
    echo "--- installing grpc ---" && \
    cd /var/local/git/grpc && \
    make -j$(nproc) && make install && make clean && ldconfig

# build grpc program
RUN mkdir /pwn
RUN chmod 777 -R /pwn
COPY entry.sh /entry.sh
COPY Makefile /pwn/Makefile
COPY grpc_server.cc /pwn/grpc_server.cc
COPY server.h /pwn/server.h
COPY server.cpp /pwn/server.cpp
COPY protobuf.proto /pwn/protobuf.proto
COPY flag.txt /pwn/flag.txt

RUN echo "-- building grpc_vuln" && \
    cd /pwn && \
    make && \
    cd /

# user maintanence
RUN groupadd ctf
RUN useradd -G ctf --home=/pwn pwnuser
RUN useradd -G ctf --home=/pwn pwnflag

RUN chown pwnflag:pwnflag /pwn/flag.txt
RUN chown pwnflag:pwnflag /pwn/grpc_server

RUN chmod 4777 /pwn/grpc_server
RUN chmod 444 /pwn/flag.txt
RUN chmod 4755 /entry.sh

EXPOSE 3010
CMD ["/entry.sh"]
