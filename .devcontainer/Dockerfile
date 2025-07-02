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

# Installation de open62541 (lib OPC UA)
RUN git clone https://github.com/open62541/open62541.git && \
    cd open62541 && \
    cmake -DUA_ENABLE_AMALGAMATION=ON . && \
    make && make install && \
    cd .. && rm -rf open62541

WORKDIR /app
CMD ["bash"]
