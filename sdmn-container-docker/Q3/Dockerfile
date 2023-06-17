FROM python:3.10
ENV PYTHONUNBUFFERED 1

WORKDIR /Code

EXPOSE 8000

RUN pip install httpserver

COPY . /Code/

CMD ["python3","./HTTPServer.py"]

