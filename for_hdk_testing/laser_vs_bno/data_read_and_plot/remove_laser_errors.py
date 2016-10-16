import os

# files = []
# for f in os.listdir():
# 	if f[-4:] == '.csv':
# 		if f[-6:-4] != '_x':
# 			files.append(f)

files = ['1901.csv']

for f in files:
	with open(f, 'r') as g:
		content = g.read()
	content_list = content.split('\n')
	for i in range(len(content_list)):
		content_list[i] = content_list[i].split(',')
	print(content_list)

	header_length = 0
	for i in range(len(content_list)):
		if not content_list[i][0][0].isalpha():
			break
			print(content_list[i][0][0])
		else:
			header_length += 1
	headers = content_list[:header_length]
	print(headers)
	content_list = content_list[header_length:]
	for i in range(len(headers)):
		headers[i] = headers[i][:-1]

	for i in range(len(content_list)):
		for j in range(len(content_list[i])):
			try:
				content_list[i][j] = float(content_list[i][j])
			except:
				pass
	for i in range(len(content_list)):
		content_list[i] = content_list[i][:-1]
	print(content_list)

	valid_data = []
	for item in content_list:
		for i in range(3):
			print(item[i])
			try:
				if item[i] < 35:
					break
			except:
				break
		else:
			print('appending')
			valid_data.append(item)

	header_str = ''
	for item in headers[0]:
		header_str += item + ','
	header_str += '\n'
	print(header_str)

	str_data = ''
	for item in valid_data:
		print(item)
		new_item = ''
		for num in item:
			new_item += str(num) + ','
		new_item += '\n'
		str_data += new_item

	print(str_data)

	with open(f + '_x', 'w') as newfile:
		newfile.write(header_str + str_data)
