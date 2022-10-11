
directory = os.environ["www/upload"].strip()
filename = body[body.find("filename") + 10:]
filename = filename[:filename.find("\"")].strip()
...
file_content = ....
if not os.path.exists(os.getcwd() + directory):
   os.umask(0)
   os.makedirs(os.getcwd() + directory, mode=0o777)
try:
   target_dir = os.path.dirname(directory)[1:]
   with open(target_dir + directory[1:] + "/" + filename, 'wb') as target:
        for line in file_content:
            target.write(line)
    message = 'The file "' + filename + '" was uploaded successfully to directory ' + target_dir
except:
    message = 'The file could not be uploaded to directory ' + target_dir


# dfile = open("datafile.txt", "rb")
# url = "http://httpbin.org/post"
# test_res = requests.post(url, files = {"form_field_name": dfile})
# if test_res.ok:
#     print(" File uploaded successfully ! ")
#     print(test_res.text)
# else:
#     print(" Please Upload again ! ")