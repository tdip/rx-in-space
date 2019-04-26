const path = require('path');
const ts = require('gulp-typescript');
const sourcemap = require('gulp-sourcemaps');
const tsProject = ts.createProject('tsconfig.json');

const buildFolder = path.resolve('build');
const tsBuildFolder = path.resolve(buildFolder, 'typescript');
const srcFolder = path.resolve('src');
const tsSrcFolder = path.resolve(srcFolder, "typescript");

gulp.task(
    'copy-rx-in-space',
    gulp.series(
        function(){
            return gulp.src([`${buildFolder}/Debug/*.{node,so}`, `${buildFolder}/Release/*.{node,so}`])
                .pipe(gulp.dest(`${buildFolder}/lib`));
        }));

gulp.task(
    'compile-ts',
    gulp.series(
        function(){
            return gulp.src(
                [`${tsSrcFolder}/**/*.ts`])
                .pipe(sourcemap.init())
                .pipe(tsProject())
                .pipe(sourcemap.write({includeContent: false, sourceRoot: tsSrcFolder}))
                .pipe(gulp.dest(tsBuildFolder));
        }));


gulp.task('compile', gulp.series('compile-ts', 'copy-rx-in-space'));

gulp.task('copy-this', gulp.series('compile', function () {
    return gulp.src([
        `${buildFolder}/**/*.{js,ts}`,
        `${buildFolder}/lib/**/*.{so,node,dll,lib}`], {base: buildFolder})
        .pipe(gulp.dest('./dist'));
}));

gulp.task('clean', () => {
    return del([buildFolder, 'dist']);
});

gulp.task('build', gulp.series('copy-this'));