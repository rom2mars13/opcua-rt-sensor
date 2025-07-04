FROM archlinux:latest

# Mise à jour + outils de base
RUN pacman -Sy --noconfirm \
    base-devel \
    cmake \
    git \
    openssl \
    mbedtls \
    curl \
    python \
    nano \
    sudo


RUN git clone https://github.com/open62541/open62541.git && \
    cd open62541 && \
    cmake \
      -DUA_ENABLE_ENCRYPTION=ON \
      -DUA_ENABLE_SUBSCRIPTIONS=ON \
      -DUA_ENABLE_METHODCALLS=ON \
      -DUA_ENABLE_NODEMANAGEMENT=ON \
      -DUA_ENABLE_ACCESS_CONTROL=ON \
      -DUA_ENABLE_DISCOVERY=ON \
      -DUA_ENABLE_USERAUTHENTICATION=ON \
      -DCMAKE_BUILD_TYPE=Release \
      . && \
    make -j && make install && \
    cd .. && rm -rf open62541

WORKDIR /app
CMD ["bash"]
