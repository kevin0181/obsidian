import os
import subprocess

def pptx_to_pdf(input_folder, output_folder):
    # 출력 폴더 없으면 생성
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 입력 폴더 안에 있는 파일들 확인
    for file in os.listdir(input_folder):
        if file.lower().endswith(".pptx"):
            input_path = os.path.join(input_folder, file)
            print(f"변환 중: {input_path}")

            # LibreOffice를 headless 모드로 실행
            subprocess.run([
                "/Applications/LibreOffice.app/Contents/MacOS/soffice",
                "--headless",
                "--convert-to", "pdf",
                "--outdir", output_folder,
                input_path
            ], check=True)

    print("✅ 변환 완료!")

# 사용 예시
if __name__ == "__main__":
    input_dir = "/Users/yuyeongbin/Desktop/obsidian/대학교/3-2/인공지능/ppt"   # PPTX가 있는 폴더
    output_dir = "/Users/yuyeongbin/Desktop/obsidian/대학교/3-2/인공지능/pdf"   # 변환된 PDF 저장할 폴더
    pptx_to_pdf(input_dir, output_dir)
