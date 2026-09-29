FROM node

RUN rm /bin/sh && ln -s /bin/bash /bin/sh
WORKDIR /home/

RUN apt -y update \
    && apt -y upgrade

RUN apt -y install cmake \
    && apt -y install build-essential  \
    && apt-get -y install manpages-dev \
    && git config --global http.sslverify false

RUN apt-get update \
    && apt-get install -y --no-install-recommends wget gnupg ca-certificates \
    && wget -q -O - https://dl.google.com/linux/linux_signing_key.pub \
       | gpg --dearmor -o /usr/share/keyrings/google-chrome.gpg \
    && echo "deb [arch=amd64 signed-by=/usr/share/keyrings/google-chrome.gpg] http://dl.google.com/linux/chrome/deb/ stable main" \
       > /etc/apt/sources.list.d/google-chrome.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends google-chrome-stable \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd /home/emsdk/ \
    && git pull \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && source ./emsdk_env.sh
