# from google import genai

# client = genai.Client(api_key="AIzaSyCTKtFITmBUAqgGcnSbUcN2w3s-Py6ecYs")


# def chatResponse(text):
#     response = client.models.generate_content(
#         model="gemini-2.0-flash", contents=text
#     )
    
#     return response.text
import google.generativeai as genai

# Cấu hình API key
genai.configure(api_key="AIzaSyCTKtFITmBUAqgGcnSbUcN2w3s-Py6ecYs")

# Tạo model
model = genai.GenerativeModel("gemini-1.5-flash")  # hoặc "gemini-1.5-pro", "gemini-pro", tùy phiên bản bạn có quyền truy cập

def chatResponse(text):
    response = model.generate_content(text)
    return response.text
