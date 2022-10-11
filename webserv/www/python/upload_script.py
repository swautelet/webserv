import requests
dfile = open("datafile.txt", "rb")
url = "http://httpbin.org/post"
test_res = requests.post(url, files = {"form_field_name": dfile})
if test_res.ok:
    print(" File uploaded successfully ! ")
    print(test_res.text)
else:
    print(" Please Upload again ! ")