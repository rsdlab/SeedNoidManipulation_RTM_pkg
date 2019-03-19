## Conversion_Mat

カメラ座標系で得られた位置姿勢をロボット座標系に変換します．

頭にカメラが搭載されている前提でSeedLifterEyeLinkKinematicsを必要とします．

## SeedLifterEyeLinkKinematics

頭にカメラが搭載されている前提でロボット座標系原点からカメラ座標系原点までの同時変換行列を計算します．

## ObstacleManager
周辺障害物の情報を定義します．SingleArUcoコンポーネントと組み合わせてマーカーに対する相対位置で障害物の位置を定義できます．

SingleArUcoコンポーネントと組み合わせない場合障害物なしを出力します．

## SeedNoid_MobileRTC

SEED-Noidの移動台車を制御するためのコンポーネントです．

速度を入力することで動作可能ですがこのパッケージではリフターのみ使用しています．

## RightSeedArmMotionPlanning_10DOF

右腕用の障害物回避軌道計画コンポーネントです．

## SeedUpperBodyRTC

SEED-Noid上半身制御用コンポーネントです．

## SeedArmPathGenerator

RightSeedArmMotionPlanning_10DOFで生成された経由点の組をなめらかにつなぐ軌道を生成します．

## SeedUpperBodyTestController

SEED-Noid Manipulation RTM pkgを動作させるためのサンプルコントローラです．