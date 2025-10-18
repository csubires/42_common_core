#!/usr/bin/env python3

import os
import time
import cgi
import html
import re

SESSION_COOKIE_NAME = 'SESSIONID'
USER_DATA_COOKIE = 'userName'

def get_cookie_value(name):
    cookie_header = os.environ.get('HTTP_COOKIE')
    if not cookie_header:
        return None

    cookies = cookie_header.split('; ')
    for cookie in cookies:
        if cookie.strip().startswith(name + '='):
            return cookie.split('=', 1)[1].strip()
    return None

def get_all_cookies():
    cookie_header = os.environ.get('HTTP_COOKIE')
    if not cookie_header:
        return {}

    result = {}
    cookies = cookie_header.split('; ')
    for cookie in cookies:
        if '=' in cookie:
            name, value = cookie.split('=', 1)
            result[name.strip()] = value.strip()
    return result

def generate_new_session_id():
    return str(int(time.time())) + "-websvrsess"

def delete_cookie(name):
    return f"Set-Cookie: {name}=; Expires=Thu, 01 Jan 1970 00:00:00 GMT; Path=/"

def sanitize_cookie_name(name):

    return re.sub(r'[^a-zA-Z0-9_-]', '', name)

def sanitize_cookie_value(value):
    return re.sub(r'[;\r\n]', '', value)


form = cgi.FieldStorage()
input_name = form.getvalue('user_name', '')
custom_cookie_name = form.getvalue('cookie_name', '')
custom_cookie_value = form.getvalue('cookie_value', '')
delete_session = form.getvalue('delete_session')
delete_name = form.getvalue('delete_name')
delete_custom = form.getvalue('delete_custom')

session_id = get_cookie_value(SESSION_COOKIE_NAME)
stored_user_name = get_cookie_value(USER_DATA_COOKIE)
all_cookies = get_all_cookies()

new_session = True
response_cookie_headers = []
message = ""
current_user_name = ""
session_message = ""
custom_message = ""

if delete_session:
    response_cookie_headers.append(delete_cookie(SESSION_COOKIE_NAME))
    session_id = None
    session_message = "🗑️ <strong>Session deleted!</strong>"
elif delete_name:
    response_cookie_headers.append(delete_cookie(USER_DATA_COOKIE))
    current_user_name = ""
    message = "🗑️ <strong>Name deleted!</strong>"
elif delete_custom and custom_cookie_name:
    clean_name = sanitize_cookie_name(custom_cookie_name)
    if clean_name:
        response_cookie_headers.append(delete_cookie(clean_name))
        custom_message = f"🗑️ <strong>Cookie '{clean_name}' deleted!</strong>"
elif custom_cookie_name and custom_cookie_value:
    clean_name = sanitize_cookie_name(custom_cookie_name)
    clean_value = sanitize_cookie_value(custom_cookie_value)
    if clean_name and clean_value:
        custom_cookie_header = f"Set-Cookie: {clean_name}={clean_value}; Max-Age=3600; Path=/; HttpOnly"
        response_cookie_headers.append(custom_cookie_header)
        custom_message = f"✅ <strong>Custom cookie set!</strong> Cookie '{clean_name}' = '{clean_value}'"
    else:
        custom_message = "❌ <strong>Error:</strong> Invalid cookie name or value"
elif input_name:
    current_user_name = html.escape(input_name)
    name_cookie_header = f"Set-Cookie: {USER_DATA_COOKIE}={current_user_name}; Max-Age=3600; Path=/; HttpOnly"
    response_cookie_headers.append(name_cookie_header)
    message = "✅ <strong>Data Stored!</strong> Your name has been saved in a cookie."
elif stored_user_name:
    current_user_name = stored_user_name
    message = "✅ <strong>Data Found!</strong> Welcome back, <strong>{}</strong> (data retrieved from cookie).".format(current_user_name)
if session_id:
    new_session = False
    if not session_message:
        session_message = "✅ <strong>Session Found!</strong> Your ID is: <strong>{}</strong>".format(session_id)
else:
    session_id = generate_new_session_id()
    session_cookie_header = f"Set-Cookie: {SESSION_COOKIE_NAME}={session_id}; Max-Age=3600; Path=/; HttpOnly"
    response_cookie_headers.append(session_cookie_header)
    session_message = "⭐ <strong>New Session Created!</strong> Your new ID is: <strong>{}</strong>".format(session_id)

bg_color = "#e6ffe6" if not new_session and stored_user_name else "#ffffe6"

print("Content-Type: text/html")
for header in response_cookie_headers:
    print(header)
print()

cookies_table = ""
if all_cookies:
    cookies_table = "<table style='width:100%; border-collapse: collapse;'>"
    cookies_table += "<tr style='background-color: #007bff; color: white;'>"
    cookies_table += "<th style='padding: 8px; text-align: left; border: 1px solid #ddd;'>Cookie Name</th>"
    cookies_table += "<th style='padding: 8px; text-align: left; border: 1px solid #ddd;'>Cookie Value</th>"
    cookies_table += "<th style='padding: 8px; text-align: left; border: 1px solid #ddd;'>Action</th>"
    cookies_table += "</tr>"

    for cookie_name, cookie_value in all_cookies.items():
        cookies_table += "<tr style='background-color: #f9f9f9;'>"
        cookies_table += f"<td style='padding: 8px; border: 1px solid #ddd;'><code>{html.escape(cookie_name)}</code></td>"
        cookies_table += f"<td style='padding: 8px; border: 1px solid #ddd;'><code>{html.escape(cookie_value[:50])}{'...' if len(cookie_value) > 50 else ''}</code></td>"

        if cookie_name not in [SESSION_COOKIE_NAME]:
            cookies_table += f"""<td style='padding: 8px; border: 1px solid #ddd;'>
                <form method="get" action="/cgi-bin/cookies.py" style="margin: 0;">
                    <input type="hidden" name="delete_custom" value="1">
                    <input type="hidden" name="cookie_name" value="{html.escape(cookie_name)}">
                    <input type="submit" value="🗑️ Delete" class="danger" style="padding: 4px 8px; font-size: 0.9em;">
                </form>
            </td>"""
        else:
            cookies_table += "<td style='padding: 8px; border: 1px solid #ddd;'>-</td>"

        cookies_table += "</tr>"

    cookies_table += "</table>"
else:
    cookies_table = "<p><em>No cookies received from client</em></p>"


html_content = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>CGI Session & Cookie Test</title>
    <style>
        body {{
            font-family: sans-serif;
            margin: 2em;
            background-color: {bg_color};
            color: #333;
        }}
        h1 {{ border-bottom: 2px solid #ccc; padding-bottom: 10px; }}
        h2 {{ color: #2c3e50; }}
        code {{ background-color: #eee; padding: 2px 4px; border-radius: 3px; }}
        .box {{
            margin: 20px 0;
            border: 1px solid #ddd;
            padding: 15px;
            background-color: #f9f9f9;
            border-radius: 5px;
        }}
        .form-group {{ margin-bottom: 15px; }}
        input[type="text"] {{
            padding: 8px;
            border: 1px solid #ccc;
            width: 250px;
            border-radius: 3px;
        }}
        input[type="submit"], button {{
            padding: 8px 15px;
            background-color: #007bff;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 3px;
            margin: 5px;
            text-decoration: none;
            display: inline-block;
        }}
        .danger {{ background-color: #dc3545 !important; }}
        .success {{ background-color: #28a745 !important; }}
        .info {{ background-color: #17a2b8 !important; }}
        .warning {{ background-color: #ffc107 !important; color: #000; }}
        .cookie-info {{
            background-color: #f8f9fa;
            padding: 10px;
            border-left: 4px solid #007bff;
            margin: 10px 0;
        }}
        label {{ font-weight: bold; display: block; margin-top: 10px; }}
    </style>
</head>
<body>
    <h1>🔐 CGI Session & Cookie Test</h1>

    <div class="box">
        <h2>Session ID Persistence Test</h2>
        <p style="font-size: 1.1em;">{session_message}</p>
        <p>Refresh the page (<strong>F5</strong>) to confirm the session ID persists.</p>

        <div class="form-group">
            <form method="get" action="{script_path}">
                <input type="hidden" name="delete_session" value="1">
                <input type="submit" value="🗑️ Delete Session" class="danger">
            </form>
        </div>
    </div>

    <div class="box">
        <h2>Data Persistence (Form & Cookie) Test</h2>
        <p style="font-size: 1.1em;">{message}</p>

        <div class="form-group">
            <form method="get" action="{script_path}">
                <label for="user_name">Enter your name:</label>
                <input type="text" id="user_name" name="user_name" value="{user_name_value}" placeholder="e.g., Jane Doe">
                <input type="submit" value="💾 Save Name" class="success">
            </form>
        </div>

        {delete_name_button}
    </div>

    <div class="box">
        <h2>🍪 Custom Cookie Creator</h2>
        <p style="font-size: 1.1em;">{custom_message}</p>

        <div class="form-group">
            <form method="get" action="{script_path}">
                <label for="cookie_name">Cookie Name:</label>
                <input type="text" id="cookie_name" name="cookie_name" placeholder="e.g., myCustomCookie" required>

                <label for="cookie_value">Cookie Value:</label>
                <input type="text" id="cookie_value" name="cookie_value" placeholder="e.g., someValue123" required>

                <input type="submit" value="🍪 Create Custom Cookie" class="warning">
            </form>
        </div>

        <p><small><strong>Note:</strong> Cookie names can only contain letters, numbers, hyphens, and underscores.</small></p>
    </div>

    <div class="box">
        <h2>📋 All Cookies (Client → Server)</h2>
        {cookies_table}
    </div>

    <div class="box">
        <h2>🔧 Technical Information</h2>
        <div class="cookie-info">
            <p><strong>Received from Client:</strong><br>
            <code>HTTP_COOKIE</code> = <code>{cookie_received}</code></p>
        </div>
        <div class="cookie-info">
            <p><strong>Sent to Client (this response):</strong><br>
            <code>Set-Cookie</code> Headers = <pre>{cookie_sent}</pre></p>
        </div>
    </div>

    <div class="box">
        <h2>🔄 Actions</h2>
        <p>
            <a href="{script_path}"><button class="info">🔄 Refresh Page</button></a>
            <a href="/"><button class="info">🏠 Go to Home</button></a>
        </p>
    </div>
</body>
</html>
""".format(
    session_message=session_message,
    message=message,
    custom_message=custom_message,
    user_name_value=html.escape(current_user_name),
    script_path='/cgi-bin/cookies.py',
    cookie_received=html.escape(os.environ.get('HTTP_COOKIE', 'No cookie received from client')),
    cookie_sent=html.escape('\n'.join(response_cookie_headers) or 'No Set-Cookie sent in this response.'),
    bg_color=bg_color,
    cookies_table=cookies_table,
    delete_name_button='<form method="get" action="{}"><input type="hidden" name="delete_name" value="1"><input type="submit" value="🗑️ Delete Name" class="danger"></form>'.format('/cgi-bin/cookies.py') if stored_user_name else ''
)

print(html_content)
