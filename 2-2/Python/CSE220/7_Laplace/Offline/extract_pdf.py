import sys

def extract_text(pdf_path):
    try:
        import fitz
        doc = fitz.open(pdf_path)
        text = ""
        for page in doc:
            text += page.get_text()
        print(text)
    except ImportError:
        try:
            import PyPDF2
            with open(pdf_path, 'rb') as f:
                reader = PyPDF2.PdfReader(f)
                text = ""
                for page in reader.pages:
                    text += page.extract_text()
                print(text)
        except Exception as e2:
            print(f"Failed completely: {e2}")

if __name__ == "__main__":
    extract_text(sys.argv[1])
