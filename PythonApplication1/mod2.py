'''
Введение в web APIs
https://developer.mozilla.org/ru/docs/Learn/JavaScript/Client-side_web_APIs/Introduction

Что такое API: технология, виды, примеры
https://gb.ru/blog/chto-takoe-api/


Как использовать Python для работы с API Google
https://sky.pro/media/kak-ispolzovat-python-dlya-raboty-s-api-google/

Работаем с API Google Drive с помощью Python
https://www.datalytics.ru/all/rabotaem-s-api-google-drive-s-pomoschyu-python/

https://github.com/googleapis/google-api-python-client
https://habr.com/ru/hubs/google_api/articles/



Первый опыт работы с Google API (на примере ContactsAPI) и OAuth2.0 на чистом HTTP
https://habr.com/ru/articles/324982/

Пишем API на Python (с Flask и RapidAPI)
https://habr.com/ru/companies/skillbox/articles/464705/


Google Drive API
https://console.cloud.google.com/apis/library/drive.googleapis.com?project=my-project-212-402315
https://developers.google.com/drive/api/reference/rest/v3/files?hl=ru

Google Sheets API
https://console.cloud.google.com/apis/library/sheets.googleapis.com?project=my-project-212-402315

Google Calendar API
https://console.cloud.google.com/apis/library/calendar-json.googleapis.com?project=my-project-212-402315

Gmail API
https://console.cloud.google.com/apis/library/gmail.googleapis.com?project=my-project-212-402315


python.exe -m pip install --upgrade pip
pip install google-api-python-client
pip install --upgrade google-api-python-client


Name: MyDrive212
ID:   mydrive212


'''

from google.oauth2 import service_account
from googleapiclient.http import MediaIoBaseDownload,MediaFileUpload
from googleapiclient.discovery import build
import pprint
import io

pp = pprint.PrettyPrinter(indent=4)

# 2 ----------------------------------------------
SCOPES = ['https://www.googleapis.com/auth/drive']
SERVICE_ACCOUNT_FILE = 'my-project-212-402315-68f7ac3f8534.json'


# 3 ----------------------------------------------
credentials = service_account.Credentials.from_service_account_file(
        SERVICE_ACCOUNT_FILE, scopes=SCOPES)
service = build('drive', 'v3', credentials=credentials)


# 20 ----------------------------------------------
print (credentials.signer_email)
# mydrive212@my-project-212-402315.iam.gserviceaccount.com


# 4 ----------------------------------------------
# results = service.files().list(pageSize=10,
#                                fields="nextPageToken, files(id, name, mimeType)").execute()
results = service.files().list().execute()


# 5 ----------------------------------------------
pp.pprint(results)

# 6 ----------------------------------------------
print(len(results.get('files')))


#=================================================
exit(0)
#=================================================


# 7 ----------------------------------------------
nextPageToken = results.get('nextPageToken')
results_for_next_page = service.files().list(pageSize=10,
                               fields="nextPageToken, files(id, name, mimeType)",
                               pageToken=nextPageToken).execute()
print (results_for_next_page.get('nextPageToken'))


# 8 ----------------------------------------------
results = service.files().list(pageSize=10,
                               fields="nextPageToken, files(id, name, mimeType)").execute()
nextPageToken = results.get('nextPageToken')
while nextPageToken:
        nextPage = service.files().list(pageSize=10,
                                        fields="nextPageToken, files(id, name, mimeType, parents)",
                                        pageToken=nextPageToken).execute()
        nextPageToken = nextPage.get('nextPageToken')
        results['files'] = results['files'] + nextPage['files']
print(len(results.get('files')))


# 9 ----------------------------------------------
results = service.files().list(
        pageSize=10, fields="nextPageToken, files(id, name, mimeType, parents, createdTime, permissions, quotaBytesUsed)").execute()


# 10 ----------------------------------------------
pp.pprint(results.get('files')[0])


# 11 ----------------------------------------------
results = service.files().list(
    pageSize=5, 
    fields="nextPageToken, files(id, name, mimeType, parents, createdTime)",
    q="'1mCCK9QGQxLDED8_pgq2dyvkmGRXhWEtJ' in parents").execute()
pp.pprint(results['files'])


# 12 ----------------------------------------------
results = service.files().list(
    pageSize=10, 
    fields="nextPageToken, files(id, name, mimeType, parents, createdTime)",
    q="name contains 'data'").execute()
pp.pprint(results['files'])


# 13 ----------------------------------------------
results = service.files().list(
    pageSize=10, 
    fields="nextPageToken, files(id, name, mimeType, parents, createdTime)",
    q="'1uuecd6ndiZlj3d9dSVeZeKyEmEkC7qyr' in parents and name contains 'data'").execute()
pp.pprint(results['files'])


# 14 ----------------------------------------------
file_id = '1HKC4U1BMJTsonlYJhUKzM-ygrIVGzdBr'
request = service.files().get_media(fileId=file_id)
filename = 'File.csv'
fh = io.FileIO(filename, 'wb')
downloader = MediaIoBaseDownload(fh, request)
done = False
while done is False:
    status, done = downloader.next_chunk()
    print ("Download %d%%." % int(status.progress() * 100))
    


# 15 ----------------------------------------------
file_id = '10MM2f3V98wTu7GsoZSxzr9hkTGYvq_Jfb2HACvB9KjE'
request = service.files().export_media(fileId=file_id,
                                             mimeType='application/vnd.openxmlformats-officedocument.spreadsheetml.sheet')
filename = '/home/makarov/Sheet.xlsx'
fh = io.FileIO(filename, 'wb')
downloader = MediaIoBaseDownload(fh, request)
done = False
while done is False:
    status, done = downloader.next_chunk()
    print ("Download %d%%." % int(status.progress() * 100))
    

# 16 ----------------------------------------------
import pandas as pd
df = pd.read_excel('/home/makarov/Sheet.xlsx')
df.head(5)


# 22 ----------------------------------------------
folder_id = '1mCCK9QGQxLDED8_pgq2dyvkmGRXhWEtJ'
name = 'Script_2.py'
file_path = '/home/makarov/Script.py'
file_metadata = {
                'name': name,
                'parents': [folder_id]
            }
media = MediaFileUpload(file_path, resumable=True)
r = service.files().create(body=file_metadata, media_body=media, fields='id').execute()
pp.pprint(r)

# 19 ----------------------------------------------
service.files().delete(fileId='1GDvLONfizF6VR7DKQaZsg_Wpdh2GFD5f').execute()


# 24 ----------------------------------------------
results = service.files().list(
    pageSize=10, 
    fields="nextPageToken, files(id, name, mimeType, parents, createdTime)",
    q="'mamby-pamby@local-grove-232309.iam.gserviceaccount.com' in owners").execute()
pp.pprint(results['files'][0:3])


# 25 ----------------------------------------------
folder_id = '1mCCK9QGQxLDED8_pgq2dyvkmGRXhWEtJ'
name = 'Sample data.csv'
file_path = '/home/makarov/sample_data_1.csv'
file_metadata = {
                'name': name,
                'mimeType': 'text/csv',
                'parents': [folder_id]
            }
media = MediaFileUpload(file_path, mimetype='text/csv', resumable=True)
r = service.files().create(body=file_metadata, media_body=media, fields='id').execute()
pp.pprint(r)


# 26 ----------------------------------------------
folder_id = '1mCCK9QGQxLDED8_pgq2dyvkmGRXhWEtJ'
name = 'Sheet from csv'
file_path = '/home/makarov/notebooks/sample_data_1.csv'
file_metadata = {
                'name': name,
                'mimeType': 'application/vnd.google-apps.spreadsheet',
                'parents': [folder_id]
            }
media = MediaFileUpload(file_path, mimetype='text/csv', resumable=True)
r = service.files().create(body=file_metadata, media_body=media, fields='id').execute()
pp.pprint(r)


# 27 ----------------------------------------------
folder_id = '1uuecd6ndiZlj3d9dSVeZeKyEmEkC7qyr'
name = 'New Folder'
file_metadata = {
    'name': name,
    'mimeType': 'application/vnd.google-apps.folder',
    'parents': [folder_id]
}
r = service.files().create(body=file_metadata,
                                    fields='id').execute()
pp.pprint(r)
