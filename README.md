# cos-insights-by-thoth

## Dependencies

```bash
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt-get update
sudo apt install cmake build-essential
sudo apt install libgtest-dev libcurl4-openssl-dev libopencv-dev libpistache-dev libsqlite3-dev
```

## ui dependencies

```bash
sudo apt-get install nodejs
# install nvm & use ghp
curl -o- https://ghp.ci/https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | sed 's,\(\(https://raw.githubusercontent.com\)\|\(https://github.com\)\),https://ghp.ci/\1,g' | bash
# upgrade nodejs
nvm install node
# switch pnpm source
pnpm config set registry https://registry.npmmirror.com
# upgrade pnpm
pnpm add -g pnpm
```