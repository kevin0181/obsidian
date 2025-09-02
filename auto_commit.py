import os
import subprocess

# === 설정 ===
CHUNK_LIMIT_MB = 300  # 300MB 단위
REMOTE = "origin"
BRANCH = "master"  # 현재 브랜치 이름
CHUNK_LIMIT = CHUNK_LIMIT_MB * 1024 * 1024

# === 함수 ===
def run_cmd(cmd):
    """명령어 실행하고 출력 실시간 표시"""
    print(f"[실행 중] {cmd}")
    result = subprocess.run(cmd, shell=True)
    if result.returncode != 0:
        print(f"[오류] 명령어 실패: {cmd}")
        exit(1)

def get_changed_files():
    """Untracked + Modified 파일 모두 반환"""
    result = subprocess.run("git status --porcelain", shell=True, capture_output=True, text=True)
    files = []
    for line in result.stdout.strip().splitlines():
        status, file_path = line[0:2], line[3:]
        # ?? → Untracked, M → Modified, A → Added
        if status.strip() in {"??", "M", "A"} and os.path.isfile(file_path):
            files.append(file_path)
    return files

def get_file_size(file_path):
    """파일 크기 (바이트 단위)"""
    return os.path.getsize(file_path)

# === 메인 로직 ===
def main():
    files = get_changed_files()
    if not files:
        print("커밋할 변경된 파일이 없습니다.")
        return

    chunk_files = []
    cur_size = 0
    chunk_num = 1

    for file in files:
        size = get_file_size(file)

        # 300MB 초과 시 이전 묶음 커밋 & 푸시
        if cur_size + size > CHUNK_LIMIT and chunk_files:
            print(f"\n[커밋 준비] Chunk {chunk_num} → {len(chunk_files)}개 파일, {cur_size / 1024 / 1024:.2f} MB")
            for f in chunk_files:
                run_cmd(f'git add "{f}"')

            run_cmd(f'git commit -m "Chunk {chunk_num}"')
            run_cmd(f"git push {REMOTE} {BRANCH}")
            print(f"[업로드 완료] Chunk {chunk_num}\n")

            # 다음 묶음 준비
            chunk_num += 1
            chunk_files = [file]
            cur_size = size
        else:
            chunk_files.append(file)
            cur_size += size

    # 마지막 묶음 처리
    if chunk_files:
        print(f"\n[커밋 준비] Chunk {chunk_num} → {len(chunk_files)}개 파일, {cur_size / 1024 / 1024:.2f} MB")
        for f in chunk_files:
            run_cmd(f'git add "{f}"')

        run_cmd(f'git commit -m "Chunk {chunk_num}"')
        run_cmd(f"git push {REMOTE} {BRANCH}")
        print(f"[업로드 완료] Chunk {chunk_num}")

    print("\n모든 변경 파일이 300MB 단위로 커밋 & 푸시 완료되었습니다!")

if __name__ == "__main__":
    main()
