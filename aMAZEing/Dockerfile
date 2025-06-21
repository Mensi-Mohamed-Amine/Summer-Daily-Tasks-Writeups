FROM debian:bookworm-slim

RUN useradd -u 1009 --no-create-home user

# Create home directory manually and set ownership
RUN mkdir -p /home/user && chown user:user /home/user

# Install build dependencies plus your existing deps
RUN apt update && apt install -y \
    build-essential \
    git \
    cmake \
    libc6 \
    protobuf-compiler \
    libprotobuf-dev \
    libnl-3-dev \
    libnl-route-3-dev \
    pkg-config \
    bison \
    flex \
    libncurses6 \
    socat \
    curl \
    ca-certificates \
    --no-install-recommends && \
    apt clean && rm -rf /var/lib/apt/lists/*


# Clone and build nsjail
RUN git clone --depth 1 https://github.com/google/nsjail.git /nsjail && \
    cd /nsjail && \
    make

# Copy nsjail binary to /usr/local/bin
RUN cp /nsjail/nsjail /usr/local/bin/ && \
    chmod +x /usr/local/bin/nsjail && \
    rm -rf /nsjail

# Copy files into /home/user and set ownership
COPY flag.txt /home/user/
COPY maze /home/user/
COPY setup_jail.sh /home/user/


RUN chmod +x /home/user/setup_jail.sh && chown -R user:user /home/user

# Run setup_jail.sh at container start
CMD ["sh", "-c", "cd /home/user && ./setup_jail.sh"]
