#include "RTS_CollisionUtils.h"
#include "Components/ShapeComponent.h"

float URTS_CollisionUtils::GetActorCollisionSize(AActor* Actor)
{
    if (!Actor)
    {
        return 0.0f;
    }

    UShapeComponent* ShapeComponent = Actor->FindComponentByClass<UShapeComponent>();
    return GetShapeCollisionSize(ShapeComponent);
}

float URTS_CollisionUtils::GetActorCollisionHeight(AActor* Actor)
{
    if (!Actor)
    {
        return 0.0f;
    }

    UShapeComponent* ShapeComponent = Actor->FindComponentByClass<UShapeComponent>();
    return GetShapeCollisionHeight(ShapeComponent);
}

float URTS_CollisionUtils::GetShapeCollisionSize(UShapeComponent* ShapeComponent)
{
    if (!ShapeComponent)
    {
        return 0.0f;
    }

    FCollisionShape CollisionShape = ShapeComponent->GetCollisionShape();

    if (CollisionShape.IsBox())
    {
        return FMath::Max(CollisionShape.Box.HalfExtentX, CollisionShape.Box.HalfExtentY) * 2;
    }
    else if (CollisionShape.IsCapsule())
    {
        return CollisionShape.Capsule.Radius * 2;
    }
    else if (CollisionShape.IsSphere())
    {
        return CollisionShape.Sphere.Radius * 2;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Unknown collision shape type for %s."), *ShapeComponent->GetOwner()->GetName());
        return 0.0f;
    }
}

float URTS_CollisionUtils::GetShapeCollisionHeight(UShapeComponent* ShapeComponent)
{
    if (!ShapeComponent)
    {
        return 0.0f;
    }

    FCollisionShape CollisionShape = ShapeComponent->GetCollisionShape();

    if (CollisionShape.IsBox())
    {
        return CollisionShape.Box.HalfExtentZ * 2;
    }
    else if (CollisionShape.IsCapsule())
    {
        return CollisionShape.Capsule.HalfHeight * 2;
    }
    else if (CollisionShape.IsSphere())
    {
        return CollisionShape.Sphere.Radius * 2;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Unknown collision shape type for %s."), *ShapeComponent->GetOwner()->GetName());
        return 0.0f;
    }
}