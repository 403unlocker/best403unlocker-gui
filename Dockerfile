FROM python:3.12.7-slim-bookworm
WORKDIR /app
RUN apt-get update
RUN apt-get install build-essential python3-pip -y
RUN pip install conan
COPY . .
RUN conan profile detect
RUN conan build . --build=missing -c tools.system.package_manager:mode=install