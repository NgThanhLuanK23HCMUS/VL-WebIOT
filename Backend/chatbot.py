from google import genai

client = genai.Client(api_key="AIzaSyCTKtFITmBUAqgGcnSbUcN2w3s-Py6ecYs")


def chatResponse(text):
    response = client.models.generate_content(
        model="gemini-2.0-flash", contents=text
    )
    
    return response.text
