#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
//This function is for step1,it shows the first three lines
//And according to step 6 and step7, fix the output
void step1(struct stat sb, char * argv) {
  if (S_ISLNK(sb.st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(argv, linktarget, 256);
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", argv, linktarget);  //the first line
  }
  else {
    printf("  File: %s\n", argv);
  }
  //the second line
  printf(
      "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu ", sb.st_size, sb.st_blocks, sb.st_blksize);

  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block special file\n");
      break;
    case S_IFCHR:
      printf("character special file\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFIFO:
      printf("fifo\n");
      break;
    case S_IFLNK:
      printf("symbolic link\n");
      break;
    case S_IFREG:
      printf("regular file\n");
      break;
    case S_IFSOCK:
      printf("socket\n");
      break;
    default:
      printf("unknown\n");
      break;
  }

  //the third line
  printf(
      "Device: %lxh/%lud\tInode: %-10lu  Links: %lu", sb.st_dev, sb.st_dev, sb.st_ino, sb.st_nlink);

  if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) {
    printf("     Device type: %d,%d\n", major(sb.st_rdev), minor(sb.st_rdev));
  }
  else {
    printf("\n");
  }
}
//this function is for step2, it shows access
void step2(struct stat sb) {
  printf("Access: (%04o/", sb.st_mode & ~S_IFMT);
  switch (sb.st_mode & S_IFMT) {  //shows the permissions
    case S_IFBLK:
      printf("b");
      break;
    case S_IFCHR:
      printf("c");
      break;
    case S_IFDIR:
      printf("d");
      break;
    case S_IFIFO:
      printf("p");
      break;
    case S_IFLNK:
      printf("l");
      break;
    case S_IFREG:
      printf("-");
      break;
    case S_IFSOCK:
      printf("s");
      break;
  }
  //output based on S_IRUSR, S_IWUSR, S_IXUSR
  switch (sb.st_mode & S_IRUSR) {
    case 0:
      printf("-");
      break;
    default:
      printf("r");
      break;
  }

  switch (sb.st_mode & S_IWUSR) {
    case 0:
      printf("-");
      break;
    default:
      printf("w");
      break;
  }

  switch (sb.st_mode & S_IXUSR) {
    case 0:
      printf("-");
      break;
    default:
      printf("x");
      break;
  }
  //output based on S_IRGRP, S_IWGRP, S_IXGRP
  switch (sb.st_mode & S_IRGRP) {
    case 0:
      printf("-");
      break;
    default:
      printf("r");
      break;
  }

  switch (sb.st_mode & S_IWGRP) {
    case 0:
      printf("-");
      break;
    default:
      printf("w");
      break;
  }

  switch (sb.st_mode & S_IXGRP) {
    case 0:
      printf("-");
      break;
    default:
      printf("x");
      break;
  }
  //output based on S_IROTH, S_IWOTH, S_IXOTH
  switch (sb.st_mode & S_IROTH) {
    case 0:
      printf("-");
      break;
    default:
      printf("r");
      break;
  }

  switch (sb.st_mode & S_IWOTH) {
    case 0:
      printf("-");
      break;
    default:
      printf("w");
      break;
  }

  switch (sb.st_mode & S_IXOTH) {
    case 0:
      printf("-)");
      break;
    default:
      printf("x)");
      break;
  }
}
//this function is for step3, shows the rest of fourth line
void step3(struct stat sb) {
  printf("  Uid: (%5d/", sb.st_uid);
  struct passwd * pwd = getpwuid(sb.st_uid);
  printf("%8s)", pwd->pw_name);
  printf("   Gid: (%5d/", sb.st_gid);
  struct group * grp = getgrgid(sb.st_gid);
  printf("%8s)\n", grp->gr_name);
}

//this function is for step4, shows the final line
void step4(struct stat sb) {
  char * atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  printf("Access: %s\n", atimestr);
  free(atimestr);
  char * mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  printf("Modify: %s\n", mtimestr);
  free(mtimestr);
  char * ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Change: %s\n", ctimestr);
  free(ctimestr);
  printf(" Birth: -\n");
}

int main(int argc, char ** argv) {
  struct stat sb;
  if (argc < 2) {  //check the input
    fprintf(stderr, "stat: missing operand\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {  //according to step5, the program can takes different arguments
    if (lstat(argv[i], &sb) == -1) {
      perror("stat");
      exit(EXIT_FAILURE);
    }
    step1(sb, argv[i]);
    step2(sb);
    step3(sb);
    step4(sb);
  }
  return EXIT_SUCCESS;
}
