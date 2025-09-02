import os
import subprocess

CHUNK_LIMIT_MB = 300
REMOTE = "origin"
BRANCH = "master"
CHUNK_LIMIT = CHUNK_LIMIT_MB * 1024 * 1024

def run_cmd(args):
    print(f"[실행] {' '.join(args)}")
    result = subprocess.run(args)
    if result.returncode != 0:
        print(f"[오류] {' '.join(args)}")
        exit(1)

def get_untracked_files():
    result = subprocess.run(["git", "ls-files", "--others", "--exclude-standard"],
                            capture_output=True, text=True, encoding="utf-8")
    files = result.stdout.strip().splitlines()
    return files  # os.path.isfile() 제거 → 한글 경로도 그대로 사용

def get_file_size(file_path):
    try:
        return os.path.getsize(file_path)
    except:
        return 0

def main():
    files = get_untracked_files()
    if not files:
        print("커밋할 새 파일이 없습니다.")
        return

    chunk_files = []
    cur_size = 0
    chunk_num = 1

    for file in files:
        size = get_file_size(file)

        if cur_size + size > CHUNK_LIMIT and chunk_files:
            print(f"\n[커밋 준비] Chunk {chunk_num} → {len(chunk_files)}개 파일, {cur_size / 1024 / 1024:.2f} MB")
            for f in chunk_files:
                run_cmd(["git", "add", f])

            run_cmd(["git", "commit", "-m", f"Chunk {chunk_num}"])
            run_cmd(["git", "push", REMOTE, BRANCH])
            print(f"[업로드 완료] Chunk {chunk_num}\n")

            chunk_num += 1
            chunk_files = [file]
            cur_size = size
        else:
            chunk_files.append(file)
            cur_size += size

    if chunk_files:
        print(f"\n[커밋 준비] Chunk {chunk_num} → {len(chunk_files)}개 파일, {cur_size / 1024 / 1024:.2f} MB")
        for f in chunk_files:
            run_cmd(["git", "add", f])

        run_cmd(["git", "commit", "-m", f"Chunk {chunk_num}"])
        run_cmd(["git", "push", REMOTE, BRANCH])
        print(f"[업로드 완료] Chunk {chunk_num}")

    print("\n모든 파일이 300MB 단위로 커밋 & 푸시 완료되었습니다!")

if __name__ == "__main__":
    main()
