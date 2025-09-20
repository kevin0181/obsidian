import os
import subprocess

def pptx_to_pdf(input_folder, output_folder):
    # 출력 폴더 없으면 생성
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # LibreOffice 실행 파일 경로 (Windows 전용)
    soffice_path = r"C:\Program Files\LibreOffice\program\soffice.exe"

    # 입력 폴더 안에 있는 파일들 확인
    for file in os.listdir(input_folder):
        if file.lower().endswith(".pptx"):
            input_path = os.path.join(input_folder, file)
            print(f"변환 중: {input_path}")

            # LibreOffice를 headless 모드로 실행
            subprocess.run([
                soffice_path,
                "--headless",
                "--convert-to", "pdf",
                "--outdir", output_folder,
                input_path
            ], check=True)

    print("✅ 변환 완료!")

# 사용 예시
if __name__ == "__main__":
    input_dir = r"C:\Users\neneee\obsidian\대학교\3-2\알고리즘/ppt"   # PPTX가 있는 폴더
    output_dir = r"C:\Users\neneee\obsidian\대학교\3-2\알고리즘\pdf"       # 변환된 PDF 저장할 폴더
    pptx_to_pdf(input_dir, output_dir)
